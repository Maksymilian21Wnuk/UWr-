import React, { useState } from "react";
import "../styles.css";
import { TodosListCheck } from "../interfaces";

export default function Todos({
  todoThings,
  setTodoThings,
  checked,
}: TodosListCheck) {
  const [input, setInput] = useState("");
  const [search, setSearch] = useState("");

  const removeTodo = (index: number) => {
    const updatedTodoThings = todoThings.filter((_, i) => i !== index);
    setTodoThings(updatedTodoThings);
  };

  return (
    <>
      <form
        onSubmit={(e) => {
          e.preventDefault();
          setSearch(input);
        }}
      >
        <input
          placeholder="Search"
          value={input}
          onChange={(e) => setInput(e.target.value)}
        />
        <button type="submit">Search</button>
      </form>
      <ul id="todo-list">
        {todoThings
          .filter(
            (todo) =>
              todo.task.includes(search) && (checked !== false || !todo.done)
          )
          .map((todo, index) => (
            <main key={index}>
              <li>
                <input
                  type="checkbox"
                  checked={todo.done}
                  onChange={() => {
                    const updatedTodoThings = [...todoThings];
                    updatedTodoThings[index] = {
                      ...updatedTodoThings[index],
                      done: !updatedTodoThings[index].done,
                    };
                    setTodoThings(updatedTodoThings);
                  }}
                />
                {todo.task}
                <div className="rm_button">
                  <button onClick={() => removeTodo(index)} />
                </div>
              </li>
            </main>
          ))}
      </ul>
    </>
  );
}
