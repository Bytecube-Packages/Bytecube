import { QueryClient, QueryClientProvider } from "react-query";
import "../styles/global.css";

const queryClient = new QueryClient();

function App({ Component, pageProps }) {
  return (
    <>
      <QueryClientProvider client={queryClient}>
        <div>
          <Component {...pageProps} />
        </div>
      </QueryClientProvider>
    </>
  );
}

export default App;
