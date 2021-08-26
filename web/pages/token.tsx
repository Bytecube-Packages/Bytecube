import React from "react";
import styles from "../styles/TokenPage.module.css";

const TokenPage = () => {
  const [token, setToken] = React.useState('');

  function revealToken() {
    let name = "access_token=";
    let decodedCookie = decodeURIComponent(document.cookie);

    if (decodedCookie.indexOf(name) > -1) {
      let start = decodedCookie.indexOf(name) + name.length;
      let end = decodedCookie.indexOf(";", start);
      if (end < 0) end = decodedCookie.length;

      let token = decodedCookie.substring(start, end);
      setToken(token);
    }
  }

  return (
    <div className={styles.token__wrapper}>
      <h1 className={styles.token__title}>Token</h1>
      <div className={styles.token__container}>
        <div className={styles.token}>{token}</div>
        <button
          className={styles.token__button}
          onClick={revealToken}
        >Reveal Token</button>
      </div>
    </div>
  );
};

export default TokenPage;