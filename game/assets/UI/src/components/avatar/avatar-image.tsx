import { tw } from "@/tailwind";
import { Image } from "@radix-ui/react-avatar";
import { forwardRef } from "react";

export const AvatarImage = forwardRef<React.ElementRef<typeof Image>, React.ComponentPropsWithoutRef<typeof Image>>(
  ({ className, ...props }, ref) => (
    <Image className={tw("aspect-square h-full w-full", className)} ref={ref} {...props} />
  ),
);
AvatarImage.displayName = Image.displayName;
