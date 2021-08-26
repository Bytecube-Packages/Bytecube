import { Package } from "../../types/Package";
import { useQuery } from "react-query";
import axios from "axios";

const PackagesPage = () => {
  const { data: allPackagesData } = useQuery("allPackagesData", async () => {
    const { data } = await axios.get(`https://api.bytecube.tk/package/list`);

    console.log(data);
    return data;
  });

  const packages = allPackagesData ?? [];

  return (
    <div>
      {
        packages.map((data: Package) => {
          return (
            <div>
              <h1>{data.name}</h1>
              <h1>{data.description}</h1>
              <h1>{data.version}</h1>
            </div>
          );
        })
      }
    </div>
  );
};

export default PackagesPage;
