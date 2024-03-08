import "./styles.css";
import { useState } from "react";
import App_info from "./components/App_info";
import { AddTodo } from "./components/Todo_list";
import { Todo } from "./interfaces";

export const initialTodoThings: Todo[] = [
  { task: "eat", done: false },
  { task: "sleep", done: false },
  { task: "repeat", done: false },
  { task: "code", done: false },
  { task: "work", done: false },
  { task: "run", done: false },
];

export default function App() {
  const [todoThings, setTodoThings] = useState(initialTodoThings);

  return (
    <div className="App">
      <App_info />
      <AddTodo todoThings={todoThings} setTodoThings={setTodoThings} />
    </div>
  );
}
