import { useRouter } from "next/router";

import styles from "../../../styles/PackagePage.module.css";

const testData = {
  id: "chrome",
  name: "Google Chrome",
  description: "Google Chrome is a web browser made by Google LLC",
  logo: "https://www.google.se/chrome/static/images/chrome-logo.svg",

  authour: {
    username: "google",
    name: "Google LLC",
  },
};

const About = () => {
  return (
    <div>
      <p>{testData.description}</p>
    </div>
  );
};

const PackagePage = () => {
  const router = useRouter();
  const { id } = router.query;

  return (
    <div>
      <div className={`${styles.package}`}>
        <div className={`${styles.package__info}`}>
          <img className={`${styles.package__logo}`} src={testData.logo} />
          <div className={`${styles.package__text}`}>
            <h2 className={`${styles.package__name}`}>{testData.name}</h2>
            <h3 className={`${styles.package__author}`}>
              by{" "}
              <span className={`${styles.author}`}>
                {testData.authour.name}
              </span>
            </h3>
          </div>
        </div>
        <button className={`${styles.package__install}`}>Install</button>
      </div>
      <div>
        <div>About</div>
        <div>Blog</div>
        <div>Versions</div>
      </div>
      <About />
    </div>
  );
};

export default PackagePage;
