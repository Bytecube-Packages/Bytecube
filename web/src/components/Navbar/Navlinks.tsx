import styles from "./Navbar.module.css";
import Link from "next/link";

export const Navlinks = () => {
  return (
    <div className={`${styles.navlinks}`}>
      <Link href="/packages">
        <a>
          <h1 className={`${styles.navlinks_important}`}>Packages</h1>
        </a>
      </Link>
      {/* TODO: Redirect to the github release for this project */}
      <Link href="/download">
        <a>
          <h1>Download</h1>
        </a>
      </Link>
      {/* TODO: Redirect to the blog written about this project */}
      {/* <Link href="https://blog.firecraftgaming.com/introducing-bytecube-cross-platform-package-manager">
        <a>
          <h1>Blog</h1>
        </a>
      </Link> */}
      <Link href="/api/auth/login">
        <a>
          <h1>Login</h1>
        </a>
      </Link>
    </div>
  );
};
