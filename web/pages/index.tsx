import { NextPage } from "next";
import React from "react";
import { Navbar } from "../src/components/Navbar";
import styles from "../styles/LandingPage.module.css";

const IndexPage: NextPage = () => (
  <>
    <Navbar />
    <div className={`${styles.body}`}>
      <div className={`${styles.tag}`}>
        <div className={`${styles.tag__text}`}>Seamlessy</div>
        <div className={`${styles.tag__text} ${styles.tag_important}`}>
          develop
        </div>
        <div className={`${styles.tag__text}`}>software</div>
      </div>
    </div>
  </>
);

export default IndexPage;
