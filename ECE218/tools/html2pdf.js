// html2pdf.js - print an HTML file to PDF with headless Chromium (Playwright)
// usage: node html2pdf.js input.html output.pdf
const path = require('path');
let playwright;
try { playwright = require('playwright'); }
catch (e) { playwright = require('/opt/node22/lib/node_modules/playwright'); }

(async () => {
  const [input, output] = process.argv.slice(2);
  if (!input || !output) {
    console.error('Usage: node html2pdf.js <input.html> <output.pdf>');
    process.exit(1);
  }
  const browser = await playwright.chromium.launch();
  const page = await browser.newPage();
  await page.goto('file://' + path.resolve(input), { waitUntil: 'networkidle' });
  await page.pdf({
    path: output,
    format: 'Letter',
    printBackground: true,
    margin: { top: '16mm', bottom: '16mm', left: '14mm', right: '14mm' },
    displayHeaderFooter: true,
    headerTemplate: '<span></span>',
    footerTemplate:
      '<div style="font-size:8px;width:100%;text-align:center;color:#888;font-family:sans-serif">' +
      '<span class="pageNumber"></span> / <span class="totalPages"></span></div>',
  });
  await browser.close();
  console.log('wrote ' + output);
})();
