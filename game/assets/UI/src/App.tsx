import { Button } from "@/components/button";
import { Card } from "@/components/card";
import { PageWrapper } from "@/components/page-wrapper";
import "@/i18n";
import { useTranslation } from "react-i18next";

import "./global.css";

function App() {
  const { t } = useTranslation();
  return (
    <PageWrapper>
      <Card>
        {t("hello")}
        <p>Make me gay!</p>
        <Button>Yes</Button>
      </Card>
    </PageWrapper>
  );
}

export default App;
