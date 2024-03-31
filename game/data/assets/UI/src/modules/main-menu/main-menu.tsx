import { Button } from "@/components/button";
import { Card } from "@/components/card";
import { useForm, zodResolver } from "@/components/form";
import { FormInput } from "@/components/input";
import { PageWrapper } from "@/components/page-wrapper";
import { tw } from "@/tw";
import { Link } from "@tanstack/react-router";
import { useState } from "react";
import { useTranslation } from "react-i18next";
import { z } from "zod";

export type SignInBodySchema = z.infer<typeof signInBodySchema>;
export const signInBodySchema = z.object({ email: z.string().email().min(1), password: z.string().min(1) });

export const MainMenu = () => {
  const [isGay, setIsGay] = useState(false);
  const { i18n, t } = useTranslation();

  const { control, handleSubmit } = useForm<SignInBodySchema>({
    defaultValues: { email: "", password: "" },
    resolver: zodResolver(signInBodySchema),
  });

  const onSubmit = handleSubmit(data => {
    console.log(JSON.stringify(data));
  });

  return (
    <PageWrapper isFooterShown={false} isHeaderShown={false}>
      <Card className={tw(" p-5", isGay && "bg-gradient-to-r from-red-500 via-yellow-500 to-green-500")}>
        {t("hello")}
        <p className="text-center hover:text-green-500">Make me gay!</p>
        <div className="flex w-full justify-around">
          <Button
            onClick={() => {
              setIsGay(true);
              i18n.changeLanguage("en");
            }}
          >
            Yes
          </Button>
          <Button
            onClick={() => {
              setIsGay(false);
              i18n.changeLanguage("ua");
            }}
          >
            Reject gayness, become a monkey!
          </Button>
        </div>

        <Card>
          <form onSubmit={onSubmit}>
            <FormInput control={control} label="Email" name="email" />
            <FormInput control={control} label="Password" name="password" type="password" />
            <div className="flex flex-col items-center gap-3">
              <Button className="w-full max-w-44" type="submit">
                Login
              </Button>
            </div>
          </form>
        </Card>
        <Link to="/settings">Go to Settings</Link>
        <div className="h-32 w-20 overflow-scroll bg-black">
          {Array.from({ length: 100 }).map(() => {
            return <p className="bg-red-200 m-0.5 h-4">Some text for scroll</p>;
          })}
        </div>
      </Card>
    </PageWrapper>
  );
};
