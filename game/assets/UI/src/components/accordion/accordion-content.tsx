"use client";

import { tw } from "@/tw";
import { Content } from "@radix-ui/react-accordion";
import { ComponentPropsWithoutRef, ElementRef, forwardRef } from "react";

export const AccordionContent = forwardRef<ElementRef<typeof Content>, ComponentPropsWithoutRef<typeof Content>>(
  ({ children, className, ...props }, ref) => (
    <Content
      className="data-[state=closed]:animate-accordion-up data-[state=open]:animate-accordion-down text-sm overflow-hidden"
      ref={ref}
      {...props}
    >
      <div className={tw("pb-4 pt-0", className)}>{children}</div>
    </Content>
  ),
);
AccordionContent.displayName = Content.displayName;
