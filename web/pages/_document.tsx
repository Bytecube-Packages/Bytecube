import Document, { Html, Head, Main, NextScript } from "next/document";

class MyDocument extends Document {
  static async getInitialProps(ctx) {
    const initialProps = await Document.getInitialProps(ctx);
    return { ...initialProps };
  }

  render() {
    return (
      <Html lang="us">
        <Head>
          <title>Bytecube Packages</title>
          <meta
            name="description"
            content="Bytecube Packages is cross platform package manager."
          />
          <meta
            name="keywords"
            content="bytecube, bytecube packages, bytecube package, bytecube packages, package manager, cross platform, social platform, voting"
          />
          <meta
            name="author"
            content="Bytecube Team"
            data-react-helmet="true"
          />
          <meta
            name="robots"
            content="index, follow"
            data-react-helmet="true"
          />
          <meta
            name="googlebot"
            content="index, follow"
            data-react-helmet="true"
          />
          <meta
            name="revisit-after"
            content="7 days"
            data-react-helmet="true"
          />
          <meta
            name="google-site-verification"
            content="rF4rXhrI3FJLF19oS8rbfqyssBpmlTG8a7FjdtWEBB0"
            data-react-helmet="true"
          />
        </Head>
        <body>
          <Main />
          <NextScript />
        </body>
      </Html>
    );
  }
}

export default MyDocument;