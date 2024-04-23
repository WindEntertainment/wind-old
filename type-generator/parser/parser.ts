import * as fs from "fs";

import { Language, MethodSchema } from "../shared";
import { parseCpp } from "./cpp-parser";
import { parseTS } from "./ts-parser";

const parsers = {
  [Language.CPP]: parseCpp,
  [Language.TS]: parseTS,
};

export const parse = ({
  language,
  outputPath,
  schemaPath,
}: {
  language: Language;
  outputPath: string;
  schemaPath: string;
}) => {
  fs.readFile(schemaPath, "utf8", (err, data) => {
    if (err) {
      console.error(`Error reading schema file '${schemaPath}':`, err);
      return;
    }

    try {
      const schema: MethodSchema = JSON.parse(data);
      const result = parsers[language](schema);

      fs.writeFileSync(outputPath, result, "utf8");
      console.log(`Classes generated successfully and written to '${outputPath}'.`);
    } catch (parseError) {
      console.error(`Error parsing schema file '${schemaPath}':`, parseError);
    }
  });
};
