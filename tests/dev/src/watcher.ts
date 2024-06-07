import chokidar from "chokidar";
import { exec, execSync, spawn } from "child_process";
import path from "path";
import debounce from "lodash/debounce";

const watchDirs = path.join(execSync("wm config-path").toString().trim().split(" ")[1], "tests");

const buildCommand = "wm";
const args = ["run", "test", "-wc"];

const runBuild = debounce(() => {
  console.log("Changes detected. Rebuilding...");
  const child = spawn(buildCommand, args);

  child.stdout.on("data", data => {
    console.log(`${data}`);
  });

  child.stderr.on("data", data => {
    console.error(`stderr: ${data}`);
  });

  child.on("close", code => {
    console.log("Finished: ", code);
  });
}, 300);

runBuild();

const watcher = chokidar.watch(watchDirs, {
  ignored: [/node_modules/, /dev/, /coverage/],
  persistent: true,
});

watcher
  .on("change", path => {
    console.log(`File ${path} has been changed`);
    runBuild();
  })
  .on("add", path => {
    console.log(`File ${path} has been added`);
    runBuild();
  })
  .on("unlink", path => {
    console.log(`File ${path} has been removed`);
    runBuild();
  });

console.log("Watching for changes...");
