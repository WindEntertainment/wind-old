import { Card } from "@/components/card";
import { PageWrapper } from "@/components/page-wrapper";
import { Link } from "@tanstack/react-router";

export const Settings = () => {
  return (
    <PageWrapper isFooterShown={false} isHeaderShown={false}>
      <Card>
        <Link to="/">Main menu</Link>
      </Card>
    </PageWrapper>
  );
};
