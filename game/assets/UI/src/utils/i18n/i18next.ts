import i18n from "i18next";
import { initReactI18next } from "react-i18next";

import ua from "../../../public/translations/ua.json";
import en from "../../../public/translations/en.json";

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
  resources,
  lng: "en",
  defaultNS,

  interpolation: {
    escapeValue: false,
  },
});

export default i18n;
