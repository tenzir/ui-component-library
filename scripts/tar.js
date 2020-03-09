const packlist = require("npm-packlist");
const tar = require("tar");
const packageDir = "./";
const versionDir = "./versions";
const readline = require("readline");
const path = require("path");
const fs = require("fs");
const semver = require("semver");

const line = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

fs.readdir(versionDir, (err, files) => {
  const highest = files
    .filter(str => str.substring(str.length - 4, str.length) === ".tgz")
    .map(str => str.substring(0, str.length - 4))
    .sort(semver.rcompare)[0];

  const [major, minor, patch] = highest.split(".");

  const versions = [
    [Number(major) + 1, minor, patch].join("."),
    [major, Number(minor) + 1, patch].join("."),
    [major, minor, Number(patch) + 1].join(".")
  ];

  console.log(`Release Type`);
  console.log(`1. Major: ${versions[0]}`);
  console.log(`2. Minor: ${versions[1]}`);
  console.log(`3. Patch: ${versions[2]}`);
  console.log(`Other input will be processed as version no.`);

  const numberedInput = input =>
    input !== "1" && input !== "2" && input !== "3";

  line.question("Version number?", version => {
    const customVersion = numberedInput(version);
    let nextVersion = customVersion ? version : versions[Number(version) - 1];

    if (!customVersion) console.log("Using exact input for version number");
    console.log(`Packing version ${nextVersion}`);

    packlist({ path: packageDir })
      .then(
        files =>
          console.log(files) ||
          tar.create(
            {
              prefix: "package/",
              cwd: packageDir,
              file: versionDir + "/" + nextVersion + ".tgz",
              gzip: true
            },
            files
          )
      )
      .then(_ => {
        console.log(`Version ${nextVersion} successfully written!`);
      })
      .catch(err => {
        console.log(`Error`);
        console.log(err);
      });

    line.close();
  });
});
