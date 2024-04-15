import React from "react";
import ReactDOM from "react-dom/client";
import App from "./App.tsx";
import { ThemeProvider } from "@emotion/react";
import "@fontsource/roboto/300.css";
import "@fontsource/roboto/400.css";
import "@fontsource/roboto/500.css";
import "@fontsource/roboto/700.css";
import CssBaseline from "@mui/material/CssBaseline";
import { blue, teal, lime, grey } from "@mui/material/colors";
import { createTheme } from "@mui/material/styles";

const theme = createTheme({
  palette: {
    mode: "light",
    primary: blue,
    secondary: teal,
    background: {
      default: grey[200], 
      paper: lime[50], 
    },
  },

  
  components: {
    MuiButton: {
      styleOverrides: {
        root: {
          margin: "5px",
          fontSize: "1.2rem",
          padding: "12px 24px", 
          size: "small",
          backgroundColor: teal[200],
          color: grey[800],
          '&:hover': {
            backgroundColor: teal[300],
          },
        },
      },
    },
    MuiIconButton: {
      styleOverrides: {
        root: {
          color: grey[800],
          '&:hover': {
            backgroundColor: teal[300],
          },
        },
      },
    },


    MuiTextField: {
      styleOverrides: {
        root: {
          margin: "5px",
        },
      },
    },
    MuiTypography: {
      styleOverrides:{
        root :{
          fontFamily: 'Roboto', 
          fontWeight: 'bold', 
          fontSize: '2rem', 
          color: lime[500], 
          textTransform: 'uppercase', 
          letterSpacing: '2px', 
        }
        }
    }

  },
});

ReactDOM.createRoot(document.getElementById("root")!).render(
  <React.StrictMode>
    <ThemeProvider theme={theme}>
      <CssBaseline />
      <App />
    </ThemeProvider>
  </React.StrictMode>
);
