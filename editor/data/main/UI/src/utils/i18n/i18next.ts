import i18n from "i18next";
import { initReactI18next } from "react-i18next";

import en from "../../../public/translations/en.json";
import ua from "../../../public/translations/ua.json";

export const defaultNS = "dreich";
export const resources = {
  en: {
    dreich: en,
  },
  ua: {
    dreich: ua,
  },
} as const;

i18n.use(initReactI18next).init({
  defaultNS,
  interpolation: {
    escapeValue: false,
  },
  lng: "en",

  resources,
});

export default i18n;
