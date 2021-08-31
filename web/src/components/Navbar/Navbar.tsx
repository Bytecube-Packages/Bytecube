import React from "react";
import styles from "./Navbar.module.css";
import Link from "next/link";
import { Navlinks } from "./Navlinks";

export const Navbar: React.FC<{ contents?: React.ReactFragment }> = ({
  contents,
}) => (
  <div className={`${styles.navbar}`}>
    <Link href="/">
      <a>
        <img src="/logo.png" alt="logo" className={`${styles.navbar__logo}`} />
      </a>
    </Link>
    <div className={`${styles.navbar__right}`}>{contents ?? <Navlinks />}</div>
  </div>
);
