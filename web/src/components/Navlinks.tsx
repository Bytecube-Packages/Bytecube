import styles from './Navbar.module.css';
import Link from 'next/link';

export const Navlinks = () => {
  return (
    <div className={`${styles.navlinks}`}>
      <Link href="/packages">
        <a>
          <h1 className={`${styles.navlinks_important}`}>Packages</h1>
        </a>
      </Link>
      <Link href="https://docs.bytecube.tk">
        <a>
          <h1>Docs</h1>
        </a>
      </Link>
      <Link href="https://blog.bytecube.tk">
        <a>
          <h1>Blog</h1>
        </a>
      </Link>
      <Link href="/api/auth/login">
        <a>
          <h1>Login</h1>
        </a>
      </Link>
    </div>
  );
};
