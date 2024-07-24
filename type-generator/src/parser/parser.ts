import * as fs from "fs";
import * as path from "path";

import { Language, MethodSchema, ParserConfigs } from "../shared";
import { parseCpp } from "./cpp-parser";
import { parseTS } from "./ts-parser";
import { format } from "./formatter";

const parsers = {
  [Language.CPP]: parseCpp,
  [Language.TS]: parseTS,
};

const languageToExtension = {
  [Language.CPP]: ".hpp",
  [Language.TS]: ".d.ts",
};

export const parse = (config: ParserConfigs) => {
  const { language, outputPath, schemaPath } = config;
  fs.readFile(schemaPath, "utf8", async (err, data) => {
    if (err) {
      console.error(`Error reading schema file '${schemaPath}':`, err);
      return;
    }

    try {
      console.log(`Processing '${schemaPath}'.`);

      const outputFilePath = outputPath + languageToExtension[language];

      const schema: MethodSchema = JSON.parse(data);

      const directoryPath = path.dirname(outputFilePath);
      if (!fs.existsSync(directoryPath)) fs.mkdirSync(directoryPath, { recursive: true });

      const result = await format(config, parsers[language](schema));
      fs.writeFileSync(outputFilePath, result, "utf8");

      console.log(`Classes generated successfully and written to '${outputFilePath}'.`);
    } catch (parseError) {
      console.error(`Error parsing schema file '${schemaPath}':`, parseError);
    }
  });
};
