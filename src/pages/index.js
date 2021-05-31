import React from "react";

const Home = ({ data }) => {
  console.log(data.site);
  return (
    <div>
      <h1>Hello</h1>
    </div>
  );
};

export default Home;

export const pageQuery = graphql`
  query MyQuery {
    site {
      siteMetadata {
        description
        siteUrl
        title
      }
    }
  }
`;
