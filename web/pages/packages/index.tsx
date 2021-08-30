import { Package } from "../../types/Package";
import { PackageCard } from "../../src/components/PackageCard/PackageCard"
import styles from '../../styles/AllPackages.module.css'
import { useQuery } from "react-query";
import { useRouter } from 'next/router'
import axios from "axios";
import Link from "next/link";

const PackagesPage = () => {
  const { data: allPackagesData } = useQuery("allPackagesData", async () => {
    const { data } = await axios.get(`https://api.bytecube.tk/package/list`);
    return data;
  });

  const packages = allPackagesData ?? [];

  return (
    <div className={styles.container}>
      {
        packages.map((data: Package) => {
          return (
            <PackageCard name={data.name} description={data.description} version={data.version} />
          );
        })
      }
    </div>
  );
};

export default PackagesPage;
