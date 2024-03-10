import { tw } from "@/tailwind";
import { forwardRef } from "react";
import { Image } from "@radix-ui/react-avatar";

export const AvatarImage = forwardRef<React.ElementRef<typeof Image>, React.ComponentPropsWithoutRef<typeof Image>>(
  ({ className, ...props }, ref) => (
    <Image ref={ref} className={tw("aspect-square h-full w-full", className)} {...props} />
  ),
);
AvatarImage.displayName = Image.displayName;
