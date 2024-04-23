import yargs from "yargs";

import { parse } from "./parser/parser";
import { Language } from "./shared";

const { language, output, schema } = yargs
  .options({
    language: {
      alias: "l",
      choices: Object.values(Language),
      demandOption: true,
      describe: "Target language",
    },
    output: {
      alias: "o",
      demandOption: true,
      describe: "Output file name",
      type: "string",
    },
    schema: {
      alias: "s",
      demandOption: true,
      describe: "Path to the schema file",
      type: "string",
    },
  })
  .help()
  .alias("help", "h")
  .parseSync();

parse({ language: language as Language, outputPath: output, schemaPath: schema });
