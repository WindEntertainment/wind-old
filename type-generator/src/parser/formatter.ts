import prettier from "prettier";
import { Language, ParserConfigs } from "../shared";

export const format = async ({ language, outputPath }: ParserConfigs, file: string) => {
  switch (language) {
    case Language.TS:
      const options = await prettier.resolveConfig(outputPath);
      return prettier.format(file, { ...options, plugins: [] });

    default:
      return file;
  }
};
