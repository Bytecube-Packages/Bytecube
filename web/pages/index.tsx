import { NextPage } from "next";

import styles from "../styles/LandingPage.module.css";

const IndexPage: NextPage = () => (
  <div>
    <div className={`${styles.navbar}`}>
      <div className={styles.navbar__logo}/>
    </div>
    <div className={`${styles.body}`}>
      <div className={`${styles.tag}`} >
        <div className={`${styles.tag__text}`}>Seamlessy</div>
        <div className={`${styles.tag__text} ${styles.tag_important}`}>develop</div>
        <div className={`${styles.tag__text}`}>software</div>
      </div>
    </div>
  </div>
);

export default IndexPage;
