export namespace JsEvents {
  namespace LoadProject {
    type Input = {
      createdAt: number;
      maps: string;
      name: string;
    };
    type Output = {
      success: boolean;
    };
  }
  export type Methods = {
    loadProject: (input: LoadProject.Input) => LoadProject.Output;
  };
}

export namespace CppEvents {
  namespace SaveProject {
    type Input = {
      createdAt: number;
      maps: string;
      name: string;
    };
    type Output = {
      success: boolean;
    };
  }
  export type Methods = {
    saveProject: (input: SaveProject.Input) => SaveProject.Output;
  };
}
