"use client";
import { tw } from "@/tw";
import { SubTrigger } from "@radix-ui/react-dropdown-menu";
import { ChevronRightIcon } from "@radix-ui/react-icons";
import { ComponentPropsWithoutRef, ElementRef, forwardRef } from "react";

export const DropdownMenuSubTrigger = forwardRef<
  ElementRef<typeof SubTrigger>,
  {
    inset?: boolean;
  } & ComponentPropsWithoutRef<typeof SubTrigger>
>(({ children, className, inset, ...props }, ref) => (
  <SubTrigger
    className={tw(
      "text-sm flex cursor-default select-none items-center rounded-sm px-2 py-1.5 outline-none focus:bg-stone-100 data-[state=open]:bg-stone-100 dark:focus:bg-stone-800 dark:data-[state=open]:bg-stone-800",
      inset && "pl-8",
      className,
    )}
    ref={ref}
    {...props}
  >
    {children}
    <ChevronRightIcon className="ml-auto h-4 w-4" />
  </SubTrigger>
));
DropdownMenuSubTrigger.displayName = SubTrigger.displayName;
