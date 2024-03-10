import { tw } from "@/tailwind";
import { ComponentProps, FC } from "react";

import { ButtonProps, buttonVariants } from "../button";
import { PaginationItem } from "./pagination-item";

type PaginationLinkProps = {
  isActive?: boolean;
} & Pick<ButtonProps, "size"> &
  Omit<ComponentProps<"a">, "ref">;

export const PaginationLink: FC<PaginationLinkProps> = ({ className, isActive, size = "icon", ...props }) => (
  <PaginationItem>
    <a
      className={tw(
        buttonVariants({
          size,
          variant: isActive ? "outline" : "ghost",
        }),
        className,
      )}
      {...props}
    />
  </PaginationItem>
);
PaginationLink.displayName = "PaginationLink";
