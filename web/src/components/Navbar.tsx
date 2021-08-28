import styles from "./Navbar.module.css";
import { Navlinks } from "./Navlinks";

export const Navbar = () => (
  <div className={`${styles.navbar}`}>
    <img src="/logo.png" alt="logo" className={`${styles.navbar__logo}`} />
    <div className={`${styles.navbar__right}`}>
      <Navlinks />
    </div>
  </div>
);