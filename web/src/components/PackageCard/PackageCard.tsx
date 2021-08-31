import React from "react";
import styles from "./PackageCard.module.css";
import Link from "next/link";

interface PackageCardProps {
  name: string;
  description: string;
  version: string;
}

//it works, now we just need to make it look better

export const PackageCard: React.FC<PackageCardProps> = ({
  name,
  description,
  version,
}) => {
  return (
    <Link href={`/packages/${name}`}>
      <a>
        <div className={styles.package}>
          <h1>{name}</h1>
          <p className={styles.version}>{version}</p>
          <p>{description}</p>
        </div>
      </a>
    </Link>
  );
};
