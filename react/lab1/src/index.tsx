import ReactDOM from "react-dom";
import { StrictMode } from "react";

import App from "./App";

const rootElement = document.getElementById("root");
const root = ReactDOM.createRoot(rootElement);

// only app in render
root.render(
  <StrictMode>
    <App />
  </StrictMode>
);
