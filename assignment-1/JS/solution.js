'use strict';

const fs = require('fs');

function countPoints(item, i, arr) {
  let pts = 0;
  for (const i in item) {
    if (i > 0) {
      const home = item[i].split(':')[0];
      const guest = item[i].split(':')[1];
      if (home > guest) pts += 3;
      else if (home === guest) pts += 1;
    }
  }
  arr[i] = [item[0], pts];
}

const data = fs.readFileSync('premiere_league.csv', 'utf8')
  .split('\r\n')
  .map((str) => str.split(','));

data.shift();

data.forEach(countPoints);
data.sort((a, b) => b[1] - a[1]);

fs.writeFileSync('results.csv', ''); // clear file if there is something in it

for (const i in data) {
  const teamResult = data[i][0] + ' ' + data[i][1] + '\n';
  fs.appendFileSync('results.csv', teamResult);
}
