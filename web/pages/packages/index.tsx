import { Package } from "../../types/Package";
import { useQuery } from "react-query";
import axios from "axios";
import Link from "next/link";

const PackagesPage = () => {
  const { data: allPackagesData } = useQuery("allPackagesData", async () => {
    const { data } = await axios.get(`https://api.bytecube.tk/package/list`);
    return data;
  });

  const packages = allPackagesData ?? [];

  return (
    <div>
      {
        packages.map((data: Package) => {
          return (
            <div>
              <Link href={`/packages/${data.name}`}>
                <a>{data.name}</a>
              </Link>
            </div>
          );
        })
      }
    </div>
  );
};

export default PackagesPage;
