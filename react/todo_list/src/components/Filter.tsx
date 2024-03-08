import React from "react";
import "../styles.css";
import { useState } from "react";
import { TodosList, Todo } from "../interfaces";

export default function FilterDone({ todoThings, setTodoThings }: TodosList) {
  // indicates whether checked was clicked
  const [checked, setChecked] = useState(0);
  // important for storing backup values
  const [backup, setBackup] = useState<Todo[]>(todoThings);
  const applyFilters = () => {
    if (!checked) {
      const filtered = todoThings.filter((todo) => todo.done);
      setBackup([...todoThings]);
      setTodoThings(filtered);
      setChecked(1);
    }
  };

  const revert = () => {
    setTodoThings(backup);
    // go back to checked 0
    setChecked(0);
  };

  return (
    <div className="filter_done">
      <button onClick={applyFilters}>Show only checked todos</button>
      <button onClick={revert}>Revert</button>
    </div>
  );
}
