import "@/i18n";
import { Outlet, createMemoryHistory, createRootRoute, createRoute, createRouter } from "@tanstack/react-router";
import { TanStackRouterDevtools } from "@tanstack/router-devtools";

import "./global.css";
import { MainMenu } from "./modules/main-menu";
import { Settings } from "./modules/settings";

const rootRoute = createRootRoute({
  component: () => {
    return (
      <>
        <Outlet />
        <TanStackRouterDevtools />
      </>
    );
  },
});

const mainMenuRoute = createRoute({
  component: MainMenu,
  getParentRoute: () => rootRoute,
  path: "/",
});

const settingsRoute = createRoute({
  component: Settings,
  getParentRoute: () => rootRoute,
  path: "/settings",
});

const routeTree = rootRoute.addChildren([mainMenuRoute, settingsRoute]);

const memoryHistory = createMemoryHistory({
  initialEntries: ["/"],
});

export const router = createRouter({ history: memoryHistory, routeTree });

declare module "@tanstack/react-router" {
  interface Register {
    router: typeof router;
  }
}
