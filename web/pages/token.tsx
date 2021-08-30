import axios from "axios";
import React from "react";
import { HiClipboardCopy } from "react-icons/hi";
import { Navbar } from "../src/components/Navbar/Navbar";
import styles from "../styles/TokenPage.module.css";

const TokenPage = () => {
  const [token, setToken] = React.useState("");
  const [tokenIsShowing, setTokenIsShowing] = React.useState(false);
  const [clipboardIsCopied, setClipboardIsCopied] = React.useState(false);

  function login() {
    window.location.href = "/api/auth/login";
  }

  async function revealToken() {
    let name = "access_token=";
    let decodedCookie = decodeURIComponent(document.cookie);

    if (decodedCookie.indexOf(name) > -1) {
      let start = decodedCookie.indexOf(name) + name.length;
      let end = decodedCookie.indexOf(";", start);
      if (end < 0) end = decodedCookie.length;

      let token = decodedCookie.substring(start, end);
      try {
        await axios.get("https://api.bytecube.tk/me", {
          headers: {
            Authorization: `Bearer ${token}`,
          },
        });
        setToken(token);
        setTokenIsShowing(true);
      } catch (_err) {
        login();
      }
    } else {
      login();
    }
  }

  async function copyToken() {
    navigator.clipboard.writeText(token);
  }

  return (
    <>
      <Navbar />
      <div className={styles.token__wrapper}>
        <h1 className={styles.token__title}>Token</h1>
        <div className={styles.token__container}>
          <div className={styles.token}>{token}</div>

          <button className={styles.token__button} onClick={revealToken}>
            {!tokenIsShowing ? "Reveal Token" : "Revealed"}
          </button>
          <button className={styles.token__copybutton}>
            {!clipboardIsCopied ? (
              <HiClipboardCopy size={50} onClick={() => copyToken()} />
            ) : (
              "Copied!"
            )}
          </button>
        </div>
      </div>
    </>
  );
};

export default TokenPage;
