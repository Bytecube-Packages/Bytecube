import axios from "axios";
import { useRouter } from "next/router";
import { useQuery } from "react-query";
import QueryString from "qs";

import styles from "../../../styles/PackagePage.module.css";
import React, { useEffect } from "react";


async function installPackage(id: string) {
  let os;
  if (navigator.appVersion.indexOf("Win") >= 0) os = "windows";
  if (navigator.appVersion.indexOf("Mac") >= 0) os = "macos";

  if (!os) return;

  const params = QueryString.stringify({
    package: id,
    platform: os,
  });

  try {
    const { data } = await axios.get(`https://api.bytecube.tk/package/install?${params}`);
    const { url } = data;

    return url
  } catch (e) {
    return;
  }
}

const Package: React.FC<{ id: string }> = ({ id }) => {
  const [downloadUrl, setDownloadUrl] = React.useState<string | null>(null);
  useEffect(() => {
    installPackage(id).then(setDownloadUrl);
  }, []);

  const { data: packageData } = useQuery("packageData", async () => {
    const params = QueryString.stringify({
      package: id
    });

    const { data } = await axios.get(`https://api.bytecube.tk/package/meta?${params}`);
    return data;
  });

  if (!packageData) {
    return <div>Loading...</div>;
  }

  return (
    <div className={styles.package}>
      <div className={styles.package__header}>
        <div className={styles.package__info}>
          <img className={styles.package__logo} src={null} />
          <div className={styles.package__text}>
            <h2 className={styles.package__name}>{packageData.name}</h2>
            {
              packageData.author &&
              <h3 className={styles.package__author}>
                by{" "}
                <span className={styles.author}>
                  {packageData.author.name}
                </span>
              </h3>
            }
          </div>
        </div>
        <button
          className={[styles.package__install, ...(downloadUrl ? [] : [styles.package_disabled])].join(" ")}
          onClick={() => {
            if (downloadUrl) window.location.href = downloadUrl;
          }}
        >Install</button>
      </div>
      <div className={styles.package__description}>
        <p>{packageData.description}</p>
      </div>
    </div>
  );
};

const PackagePage = () => {
  const router = useRouter();
  const { id } = router.query;

  if (!id) {
    return <div>Loading...</div>
  }

  return (
    <Package id={id as string} />
  );
};

export default PackagePage;
