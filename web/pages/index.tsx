import { NextPage } from "next";
import React from "react";
import { Navbar } from "../src/components/Navbar/Navbar";
import styles from "../styles/LandingPage.module.css";

const combine = (...classes) => classes.join(" ");
const IndexPage: NextPage = () => {
  return (
    <>
      <Navbar />
      <div className={styles.body}>
        <div className={styles.landing}>
          <div className={styles.main}>
            <div className={styles.tag}>
              <div className={styles.tag__text}>Seamlessy</div>
              <div className={combine(styles.tag__text, styles.tag_important)}>
                develop
              </div>
              <div className={styles.tag__text}>software</div>
            </div>
            <div className={styles.main__text}>
              Install Bytecube today and make installing software so much easier and make creating and publishing software a lot easier too.
            </div>
            <button className={styles.main__start}>Get Started</button>
          </div>
          <img className={styles.landing__cli} src="/cli.svg" alt="CLI" />
        </div>
      </div>
    </>
  )
};

export default IndexPage;
