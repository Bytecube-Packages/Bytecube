import { NextPage } from "next";
import React from "react";
import { Navbar } from "../src/components/Navbar/Navbar";
import styles from "../styles/DownloadPage.module.css";
import { AiOutlineDownload } from "react-icons/ai";
import { useRouter } from "next/router";

const combine = (...classes) => classes.join(" ");
const IndexPage: NextPage = () => {
  const router = useRouter();

  return (
    <>
      <Navbar />
      <h1 className={styles.header}>Download Bytecube</h1>
      <div className={styles.card}>
        <div className={styles.container}>
          <h1
            className={styles.windows}
            onClick={() =>
              router.push(
                "https://github.com/Bytecube-Packages/Bytecube/releases/download/v1.0.0/install_bytecube.exe"
              )
            }
          >
            Windows{" "}
            <span>
              <AiOutlineDownload size={35} />
            </span>
          </h1>

          <h1
            className={styles.macos}
            onClick={() =>
              router.push(
                "https://github.com/Bytecube-Packages/Bytecube/releases/download/v1.0.0/install_bytecube.pkg"
              )
            }
          >
            MacOS{" "}
            <span>
              <AiOutlineDownload size={35} />
            </span>
          </h1>
        </div>
      </div>
    </>
  );
};

export default IndexPage;
