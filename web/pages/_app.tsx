import "../styles/global.css";

function App({ Component, pageProps }) {
  return (
    <>
      <div>
        <Component {...pageProps} />
      </div>
    </>
  );
}

export default App;