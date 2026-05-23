const canvas = document.getElementById('latticra-light');
const context = canvas.getContext('2d');
const reduceMotion = window.matchMedia('(prefers-reduced-motion: reduce)').matches;
let tick = 0;

function resizeCanvas() {
  const ratio = Math.min(window.devicePixelRatio || 1, 2);
  canvas.width = Math.floor(window.innerWidth * ratio);
  canvas.height = Math.floor(window.innerHeight * ratio);
  canvas.style.width = `${window.innerWidth}px`;
  canvas.style.height = `${window.innerHeight}px`;
  context.setTransform(ratio, 0, 0, ratio, 0, 0);
}

function drawFrame() {
  const width = window.innerWidth;
  const height = window.innerHeight;
  const centerX = width / 2;
  const centerY = height / 2;
  const count = Math.min(999, Math.floor(Math.max(width, height) * 0.8));

  context.fillStyle = 'rgba(0, 0, 0, 0.12)';
  context.fillRect(0, 0, width, height);
  context.font = '16px ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, monospace';
  context.textAlign = 'center';
  context.textBaseline = 'middle';

  for (let i = count; i > 0; i -= 1) {
    const radius = i / 2.05;
    const angleX = i / 8.5 + tick / 42;
    const angleY = i / 7.25 + tick / 52;
    const hue = (188 + i / 3 + tick / 2) % 360;
    const alpha = 0.16 + (i % 9) / 22;
    const x = centerX + Math.cos(angleX) * radius;
    const y = centerY + Math.sin(angleY) * radius;

    context.fillStyle = `hsla(${hue}, 100%, 64%, ${alpha})`;
    context.fillText(i & 1 ? '✦' : '0', x, y);
  }

  tick += reduceMotion ? 0.12 : 1;
  window.requestAnimationFrame(drawFrame);
}

window.addEventListener('resize', resizeCanvas, { passive: true });
resizeCanvas();
context.fillStyle = '#000';
context.fillRect(0, 0, window.innerWidth, window.innerHeight);
drawFrame();
