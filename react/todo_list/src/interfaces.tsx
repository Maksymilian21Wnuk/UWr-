import React from "react";

export interface Todo {
  task: string;
  done: boolean;
}

export interface TodosList {
  todoThings: Todo[];
  setTodoThings: React.Dispatch<React.SetStateAction<Todo[]>>;
}

export interface Backup {
  backup: Todo[];
  setBackup: React.Dispatch<React.SetStateAction<Todo[]>>;
}
