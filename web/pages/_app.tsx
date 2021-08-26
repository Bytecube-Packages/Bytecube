import { QueryClient, QueryClientProvider } from "react-query";
import "../styles/global.css";

const queryClient = new QueryClient();

function App({ Component, pageProps }) {
  return (
    <>
      <QueryClientProvider client={queryClient}>
        <Component {...pageProps} />
      </QueryClientProvider>
    </>
  );
}

export default App;
