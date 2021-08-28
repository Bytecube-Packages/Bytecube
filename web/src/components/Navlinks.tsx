import styles from "./Navbar.module.css";

export const Navlinks = () => {
  return (
    <div className={`${styles.navlinks}`}>
      <h1 className={`${styles.navlinks_important}`}>Packages</h1>
      <h1>Docs</h1>
      <h1>Blog</h1>
      <h1>Login</h1>
    </div>
  );
};