#!/usr/bin/env python3
"""md2pdf.py - turn a solutions Markdown file into a styled PDF (Arabic + English).

usage: python3 md2pdf.py input.md output.pdf [--html out.html]

Markdown extras:
  * Arabic explanation blocks:
        <div class="ar" markdown="1">
        ... Arabic text ...
        </div>
  * Inside Arabic text, write any English word / code token as [[token]].
    It is rendered on its OWN line (left-to-right), so mixed Arabic/English
    never scrambles the reading order.
  * Fenced code blocks (```cpp) get syntax highlighting.
"""
import html
import os
import re
import subprocess
import sys

from markdown_it import MarkdownIt
from pygments import highlight as pyg_highlight
from pygments.formatters import HtmlFormatter
from pygments.lexers import get_lexer_by_name
from pygments.util import ClassNotFound


def highlight(code, lang, attrs):
    """Syntax-highlight fenced code; unknown/empty language -> plain block."""
    try:
        lexer = get_lexer_by_name(lang or "text")
    except ClassNotFound:
        lexer = get_lexer_by_name("text")
    return pyg_highlight(code, lexer, HtmlFormatter(nowrap=True))  # markdown-it wraps it in <pre><code>

HERE = os.path.dirname(os.path.abspath(__file__))

CSS = """
@page { size: Letter; }
:root { --ink:#1b1f24; --muted:#5b6470; --line:#d9dee5; --accent:#1f5fa8; --soft:#f4f7fb;
        --ok:#1e7a46; --warn:#9a5b00; }
html { -webkit-print-color-adjust: exact; print-color-adjust: exact; }
body { font-family: "Noto Sans", "DejaVu Sans", sans-serif; color: var(--ink);
       font-size: 10.5pt; line-height: 1.5; margin: 0; background: #fff; }
h1 { font-size: 20pt; color: var(--accent); margin: 0 0 4pt; }
h2 { font-size: 14.5pt; color: var(--accent); border-bottom: 1.5pt solid var(--accent);
     padding-bottom: 2pt; margin: 18pt 0 8pt; break-after: avoid; }
h3 { font-size: 12pt; margin: 14pt 0 6pt; break-after: avoid; }
h4 { font-size: 10.5pt; margin: 10pt 0 4pt; color: var(--muted); break-after: avoid; }
p { margin: 4pt 0; }
code { font-family: "Noto Sans Mono", "DejaVu Sans Mono", monospace; font-size: 9pt;
       background: var(--soft); padding: 0 2pt; border-radius: 2pt; }
pre { background: #f6f8fa; border: 0.75pt solid var(--line); border-radius: 4pt;
      padding: 6pt 8pt; font-size: 8.6pt; line-height: 1.35; overflow: hidden;
      white-space: pre-wrap; word-break: break-word; }
pre code { background: none; padding: 0; font-size: inherit; }
table { border-collapse: collapse; margin: 6pt 0; font-size: 9.5pt; break-inside: avoid; }
th, td { border: 0.75pt solid var(--line); padding: 3pt 6pt; vertical-align: top; }
th { background: var(--soft); }
blockquote { margin: 6pt 0; padding: 4pt 10pt; border-left: 3pt solid var(--accent);
             background: var(--soft); }
.q { background: var(--soft); border-left: 3pt solid var(--accent); padding: 5pt 9pt;
     margin: 8pt 0; font-weight: 600; break-inside: avoid; }
.ans-label { color: var(--ok); font-weight: 700; }
.ar { direction: rtl; text-align: right; font-family: "Noto Naskh Arabic", "Noto Sans Arabic", serif;
      font-size: 12pt; line-height: 1.9; background: #fbfaf5; border-right: 3pt solid #c9a227;
      padding: 6pt 10pt; margin: 8pt 0; border-radius: 3pt; }
.ar h3, .ar h4 { color: #7a5b00; }
.ar ul, .ar ol { padding-right: 18pt; padding-left: 0; }
.en-line { display: block; direction: ltr; unicode-bidi: isolate; text-align: right;
           font-family: "Noto Sans Mono", "DejaVu Sans Mono", monospace; font-size: 9.5pt;
           color: #1f3b63; margin: 1pt 0; }
.cover { border-bottom: 2pt solid var(--accent); margin-bottom: 10pt; padding-bottom: 6pt; }
.cover .sub { color: var(--muted); }
.pagebreak { break-after: page; }
"""


def protect_code(text):
    """Pull out fenced code and inline code so [[...]] replacement never touches them."""
    stash = []

    def keep(m):
        stash.append(m.group(0))
        return "\x00%d\x00" % (len(stash) - 1)

    text = re.sub(r"```.*?```", keep, text, flags=re.S)
    text = re.sub(r"`[^`\n]+`", keep, text)
    return text, stash


def restore_code(text, stash):
    return re.sub(r"\x00(\d+)\x00", lambda m: stash[int(m.group(1))], text)


def convert(md_text):
    text, stash = protect_code(md_text)
    # [[token]] -> its own LTR line; kept out of Markdown so '*', '_' stay literal
    en_lines = []

    def en(m):
        en_lines.append('<span class="en-line">%s</span>' % html.escape(m.group(1)))
        return "ENLINEPH%04dX" % (len(en_lines) - 1)

    text = re.sub(r"\[\[(.+?)\]\]", en, text)
    text = restore_code(text, stash)
    # HTML wrapper lines (<div ...> / </div>) need blank lines around them so the
    # Markdown inside is still parsed (CommonMark HTML-block rule)
    text = re.sub(r"^(<div[^>]*>)[ \t]*$", r"\1\n", text, flags=re.M)
    text = re.sub(r"^(</div>)[ \t]*$", r"\n\1\n", text, flags=re.M)
    md = (MarkdownIt("commonmark", {"html": True, "highlight": highlight})
          .enable("table").enable("strikethrough"))
    body = md.render(text)
    body = re.sub(r"ENLINEPH(\d{4})X", lambda m: en_lines[int(m.group(1))], body)
    pyg = HtmlFormatter(style="friendly").get_style_defs("pre")
    return ("<!doctype html><html><head><meta charset='utf-8'>"
            "<style>%s\n%s\npre{background:#f6f8fa}</style></head><body>%s</body></html>"
            % (CSS, pyg, body))


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(1)
    src, out = sys.argv[1], sys.argv[2]
    html_out = out[:-4] + ".html" if out.endswith(".pdf") else out + ".html"
    if "--html" in sys.argv:
        html_out = sys.argv[sys.argv.index("--html") + 1]
    with open(src, encoding="utf-8") as f:
        page = convert(f.read())
    with open(html_out, "w", encoding="utf-8") as f:
        f.write(page)
    subprocess.run(["node", os.path.join(HERE, "html2pdf.js"), html_out, out], check=True)


if __name__ == "__main__":
    main()
