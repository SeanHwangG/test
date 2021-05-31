# Database

| Sql                       | NoSQL                                                          |
| ------------------------- | -------------------------------------------------------------- |
| ACID compliance           | scalability (variaty of data), processing speed (high traffic) |
| structured and unchanging | cloud computing, storage / Rapid development                   |

* DynamoDB: Schemaless db, storing basic user attributes in an object-based format
* Neptune: high-performance graph database optimized for processing graph queries
* Redshift: large streams of user activity data

> Terms

* Data parallelism: parallelization across multiple processors focusing on distributing data across different nodes
  * can be applied on regular data structures like arrays and matrices by working on each element in parallel

* ETL (Extraction, Translation, Loading)
  ![ETL](images/20210304_233925.png)

* Execution model: Batch vs Streaming

* integration: combining data from different sources into a single, unified view
  * Reduce data complexity | Adds value to data | Increase collaboration, availability | Unify data system

* Lambda Architecture
  * data-processing architecture designed to handle massive quantities of data both batch, stream processing

* Latency
  * Low: Game, Traffic
  * High: Search engine indexing

* ORM (Object Relation Mapping): Remove dependency: Doesn't depends on speicific database (MySQL, MongoDB)
  * Reduce error, automatically detect changes

* Schema on read: creates the schema only when reading the data → NoSql

* Schema on write: defined as creating a schema for data before writing into the database → SQL

* smart: Connect with other devices and have knowledge of the environment

* in situ: Bringing the computation to the location of the data

* rollback: process that reverts writes operations to ensure the consistency of all replica set members

* sharding: architecture that partitions data by key ranges, distributes data among two or more database instances
  * enables horizontal scaling

* CAP
  * Can only achieve two of following
  * Consistency: Every read receives the most recent write or an error
  * Availability: Every request receives response, without guarantee that it contains the most recent write
  * Partition: Continues to operate despite any number of messages dropped by network between nodes

![CAP Theory](images/20210304_233840.png)

* ACID
  * Atomicity: all changes that we need to do for these promotions must happen altogether
  * Concurrency: multiple people updating a database simultaneously
  * Isolation: context of concurrency, multiple people updating a database simultaneously
  * Durability: once a transaction has been committed, it will remain so

* BASE
  * Basic Availability, Soft state, Eventual Consistency

* Fault Tolerance
  * enables a system to continue operating properly in the event of the failure of some of its components
  * Commodity cluster \(redundant data storage\)

* IaaS
  * User must install and maintain an operating system, and other applications
  * virtual machines, servers, storage, load balancers, network
  * Amazon EC2 cloud
* PaaS
  * Provided with entire computing platform
  * Execution runtime, database, web server, development tools
  * Google App engine, Microsoft Azure
* SaaS
  * cloud service provides hardware, software environment \(operating system, application software\)
  * Dropbox
* BDMS
  * Continuous data ingestion
  * Support for common “Big Data” data types
  * A full query language
  * A flexible semi-structured data model

> Sample questions

* 6V of Big data
  * Volumes: brings cost, scalability, and performance related to their storage access and processing
  * Variety: structure (formats, models), media, semantic(interpret), availability(realtime vs intermittent)
  * Velocity: Data is being generated at an alarming rate (batch processing vs real-time processing)
  * Veracity: Uncertainty and inconsistencies in the data (data provenance)
  * Valence: Connectedness of big data in form of graphs (Complex Data Exploration Algorithm)
  * Value: Finding correct meaning out of the data

* How to solve challenges in big data integration?
  * Probabilistic Schema Mapping vs Pay-as-you-go Model

* 5 key points in order to categorize big data systems?
  * Execution model, Latency, Scalability, Programming Language, Fault Tolerance

* Why do companies use big data?
  * Higher scales | Improved Safety | Customer Satisfaction | Better Profit Margins
  * Efficient operations | Improved Product Placement (Personalized marketing)

* Why is it rising?
  * Access of larger storage becomes easier for everyone

* Why is mobile advertising related to big data?
  * Mobile advertising benefits from data integration with location which requires big data

* What are Big data policies?
  * privacy and lifetime | interoperability and regulation | curation and quality

* What is denormalization of data?
  * improve the read performance, at expense of write performance, add redundant copies | grouping data

* Three types of source: Business data | Sensor data | User data
* Things to take account
  * Frequency of updates | Consolidation rule → linking, missing data, dirty data (negative age)

## Data Science

> Terms

* Transaction: a single logical operation on the data → must provide ACID
* Lake: vast pool of raw data, the purpose for which is not yet defined
* Warehouse:* repository for structured, filtered data that has already been processed for a specific purpose
* Silo: Data produced from an organization that is spread out
  * Bad unsynchronized and invisible data
  ![Silo](images/20210304_233808.png)
* Data Analyst: Discover Problem & Potential solution → Visualize, dashboard
  * Focus on Past & Present
* Scientist: Modeling
* Data Engineer
  * Data Architecture, Database maintenance \(Schema\), quality and pipelines

* Data Science

![Data Science](images/20210304_233946.png)

* Dashboard: promotes trasnparency, accountability
  * automatic data pipelines: dashboard
  * purpose, scope, layout + flow, consistent naming structure

## B Tree

* Every node has at most M children
* Every internal node has at least ⌈M|2⌉children
* The root has at least 2 children if it is not a leaf
* An internal node with k children contains k - 1 keys
* All leaves appear on the same level of the tree
* Property
  * parameter n: a node holds n search key values (sorted) and n+1 pointers (to interior nodes or records)
  * left key ≤ pointed-to value < right key
  * choose n so large that a node fits in a block
  * interior node: between half and all of the n+1 pointers are used
  * leaf node: rightmost pointer to the next leaf

> Exampel : B+ Tree

* Internal nodes contain only search keys (no data)
* leaves have at least ⌈L | 2⌉ keys up to L keys
* Balanced (equal length paths) trees for minimizing disk I|O
* logarithmic levels maintained w.r.t. size of the data file
* no overflow blocks (but insert, delete more complex)
* guaranteed upper limits on access, insert, delete times
* data file not sorted, then leafs have to constitute a dense index
* data file sorted, then leafs may constitute a sparse index
* number of children for a node, ⌈b | 2⌉ m  b     (only root can have two children)
* In order to access a particular byte, track #, sector #, offset needed
* Each block usually contains 512 bytes
* Data must be brought to main memory (RAM)

## DB Index

* Data structures used for quickly locating tuples that meet a specific type of condition ([ex] equality, range)
* Many types of indexes. Evaluate them on access, insertion, deletion item, Disk Space needed

* Primary index: the index on the attribute (a.k.a. search key) that determines the sequencing of the table on disk

* Secondary index: index on any other attribute

* Dense index: every value of the indexed attribute appears in theindex

* Sparse index: many values do not appear

* insertion: if no new block is created then do nothing else create an index entry with the new value
  * how to find space: find nearby free space and slide blocks backward, or use an overflow block

* deletion: if the deleted entry appears in the index replace it with the next search-key value
  * (leave deleted value assuming no part of the system assume it still exists without checking the block)

* Multi-level indices: treat the index as data and build an index on it

## Key

* Auto increment: Surrogate keys never need to change, even if all other columns in your table are possible to change
  * easier for RDBMS to ensure uniqueness without locking, race conditions, when users inserting concurrently
  * Int is most compact data type you can use for primary key, so it results in a smaller index than using a long string
  * Efficiency of inserting into B-tree indexes
* Alternative: combination of columns that could be a primary key, but isn't
* Candidate: Minimal Super Keys
* Foriegn
  * FOREIGN KEY (PersonID) REFERENCES Persons(PersonID)
  * PersonID column in the Orders table is a FOREIGN KEY in the Orders table
* Primary: Chosen candidate keys
  * cannot have null values in any tuple, table can have only one primary
* Super: A set of attributes SK of R such that no two tuples in any valid
  * relation instance r(R) will have the same value for SK
* composite: candidate key that consists of two+ aattributes (table columns) that together uniquely identify entity
* compound: composite key for which each attribute that makes up the key is a simple (foreign) key in its own right
* Natural Key
  * if column has some meaning for the entity, (ex. phone number) no extra column is needed for the surrogate key
  * table of shoes referencing colors would need to do a join if you wanted to get the color name

### UUID

* no network connection between multiple databases
* avoids attackers guessing url's to pages they shouldn't have access to

{% tabs %}
{% tab title='javascript' %}

> celebrate

```js
import { Joi, celebrate } from "celebrate";
const SaleValidation = Joi.object()
  .keys({
    name: Joi.string().min(1).max(10).required(), amount: Joi.number().min(0).optional(),
    percent: Joi.number().min(0).max(1).optional(),
  })
  .or("amount", "percent")
  .nand("amount", "percent");

export default {
  saleAdd: celebrate({ body: BuyFormValidation, }),
  saleGet: celebrate({ params: { name: Joi.string().min(1).max(10).required() } }),
  saleUpdate: celebrate({ params: { uuid: Joi.string().guid({ version: "uuidv4" }).required() } }),
  saleDelete: celebrate({ params: { uuid: Joi.string().guid({ version: "uuidv4" }).required() } }),
};

// Types
const schema = Joi.object().keys({
  type: Joi.string().valid('ios', 'android'),
});
```

{% endtab %}
{% endtabs %}

## Design

> Terms

* Functional Dependency
  * A->B holds if two tuples having same value of attribute A also have same value for attribute B

| STUD_NO | STUD_NAME | STUD_PHONE | STUD_STATE | STUD_COUNT RY | STUD_AG E |
| ------- | --------- | ---------- | ---------- | ------------- | --------- |
| 1       | RAM       | 9716271721 | Haryana    | India         | 20        |
| 2       | RAM       | 9898291281 | Punjab     | India         | 19        |
| 3       | SUJIT     | 7898291981 | Rajsthan   | India         | 18        |
| 4       | SURESH    |            | Punjab     | India         | 21        |

* Functional Dependencies STUD_NO->STUD_NAME, STUD_NO->STUD_PHONE hold but STUD_NAME->STUD_STATE do not hold

* Normalize
  * process of minimizing redundancy from a relation or set of relations

* One to Many

![One to Many](images/20210321_212309.png)

* Many to Many: Requires intermediary table

![Many to Many](images/20210321_212400.png)

* {STUD_NO -> STUD_NAME, STUD_NO -> STUD_STATE, STUD_STATE -> STUD_COUNTRY, STUD_NO -> STUD_AGE}

```sql
STUDENT (STUD_NO, STUD_NAME, STUD_PHONE, STUD_STATE, STUD_AGE)
STATE (STATE, COUNTRY)
```

* Algebra

* Projection

$$ \pi%0 $$

* Selection

$$ \sigma $$

* Union

$$ \cup $$

* Difference

$$ - $$

* Join

$$ \bowtie $$

* Attribute Renaming

$$ \delta $$

{% tabs %}
{% tab title='sql' %}

```sh
# Find theaters showing movies by Bertolucci
{t : theater |  s ∈ schedule  m ∈ movie
  [t(theater) = s(theater) ∧ s(title) = m(title) ∧ m(director) = Bertolucci}

# Find the titles of all movies by “Berto”
{t: title| ∃m ∈ movie [m(director) = “Berto” ∧ t(title) = m(title)]}

# Find the pairs of actors acting together in some movie
π actor 1, actor2 ( δactor → actor1 (movie) ⋈ δactor → actor2( movie ) )

# Find the actors playing in every movie by Berto
π actor ( movie ) - πactor [ ( πactor ( movie ) ⋈ πtitle ( σdir=BERTO( movie ) ) ) - πactor, title( movie ) ]

# Find the actors playing in every movie by Berto
π title,actor(movie) ÷ πtitle(σdir=berto(movie))

# Find the names of customers who took every loan.
π cname,lno(borrower) ÷ π lno(δ no → lno(loan))     # fail when loan is empty
π name(customer) - πname ( πname(customer) ⋈ πno(loan) - δcname→name, lno→no(πcname,lno(borrower)) )

# List the directors such that every actor is cast in one of his|her movies.
π director,actor(movie) ÷ πactor(movie).        # fail when there is no actor
π director(movie) − πdirector[πdirector(movie) ⋈ πactor(movie) − πdirector,actor(movie)]

# The directors of all movies playing elsewhere than Hillcrest
π director[σtheater ≠ ‘Hillcrest’(movie ⋈ schedule)]    || expensive join
π director[π title, director(movie) ⋈ πtitle(σtheater ≠ 'Hillcrest'(schedule))]

# List the drinkers that frequent only bars that serve some beer that they like.
# (Assume each drinker likes at least one beer and frequents at least one bar.)
[frequents | drinker bar]
[serves | bar beer]
[likes | drinker beer]

πdrinker(frequents) − πdrinker[frequents−πdrinker,bar(serves ⋈ likes)]

# List the drinkers that frequent no bar that serves a beer that they like
πdrinker(frequents) − πdrinker(frequents ⋈ serves ⋈ likes)
```

{% endtab %}
{% endtabs %}

### Normal Form

> First Normal Form

* Relation is in first normal form if it does not contain any composite or multi-valued attribute
* There are only Single Valued Attributes
* Attribute Domain does not change
* There is a Unique name for every Attribute/Column
* The order in which data is stored, does not matter

| STUD_NO | STUD_NAME | STUD_PHONE             | STUD_STATE | STUD_COUNTRY |
| ------- | --------- | ---------------------- | ---------- | ------------ |
| 1       | RAM       | 9716271721, 9871717178 | HARYANA    | INDIA        |
| 2       | RAM       | 9898297281             | PUNJAB     | INDIA        |
| 3       | SURESH    |                        | PUNJAB     | INDIA        |

* Multi-valued attributes in the table

| STUD_NO | STUD_NAME | STUD_PHONE | STUD_STATE | STUD_COUNTRY |
| ------- | --------- | ---------- | ---------- | ------------ |
| 1       | RAM       | 9716271721 | HARYANA    |              |
| 1       | RAM       | 9871717178 | HARYANA    | INDIA        |
| 2       | RAM       | 9898297281 | PUNJAB     | INDIA        |
| 3       | SURESH    |            | PUNJAB     | INDIA        |

> Second Normal Form

* a relation must be in first normal form and relation must not contain any partial dependency
* dependent on any proper subset of any candidate key of the table
* [-] If we update only one tuple and not the other, the database would be in an inconsistent state

* Question: Make following table into 2NF

| STUD_NO | COURSE_NO | COURSE_FEE |
| ------- | --------- | ---------- |
| 1       | C1        | 1000       |
| 2       | C2        | 1500       |
| 1       | C4        | 2000       |
| 4       | C3        | 1000       |
| 4       | C1        | 1000       |
| 2       | C5        | 2000       |

* COURSE_FEE cannot alone decide the value of COURSE_NO or STUD_NO;
* COURSE_FEE together with STUD_NO cannot decide the value of COURSE_NO;
* COURSE_FEE together with COURSE_NO cannot decide the value of STUD_NO;
* COURSE_FEE would be a non-prime attribute, as it does not belong to one only candidate key {STUD_NO, COURSE_NO}
  * But, COURSE_NO -> COURSE_FEE, which is a proper subset of the candidate key
* Non-prime attribute COURSE_FEE is dependent on a proper subset of the candidate key, which is a partial dependency
  * so this relation is not in 2NF

| Table 1 |           | Table 2   |
| ------- | --------- | --------- | ---------- |
| STUD_NO | COURSE_NO | COURSE_NO | COURSE_FEE |
| 1       | C1        | C1        | 1000       |
| 2       | C2        | C2        | 1500       |
| 1       | C4        | C3        | 1000       |
| 4       | C3        | C4        | 2000       |
| 4       | C1        | C5        | 2000       |
| 2       | C5        |

> Third Normal Form

* reduce the duplication of data, avoid data anomalies, ensure referential integrity, simplify data management
* free of insertion, update, deletion anomalies, and ensures functional dependency preserving and lossless

| STUD_NO | STUD_NAME | STUD_STATE | STUD_COUNTRY | STUD_AGE |
| ------- | --------- | ---------- | ------------ | -------- |
| 1       | RAM       | HARYANA    | INDIA        | 20       |
| 2       | RAM       | PUNJAB     | INDIA        | 19       |
| 3       | SURESH    | PUNJAB     | INDIA        | 21       |

## Relation

{% tabs %}
{% tab title='hasone.js' %}

* A HasOne B association
  * 1-1 relationship exists between A and B
  * foreign key being defined target B
* A HasMany B association
  * 1-n relationship exists between A and B
  * foreign key being defined in the target model (B)
* A BelongsTo B association
  * 1-1 relationship exists between A and B
  * foreign keys being defined in the source model (A)
  * should be added when we need an owner
  * Book.belongsTo(models.User)
* A BelongsToMany B association: n-n relationship exists between A and B, using table C as junction table
  * Table C has the foreign keys (automatically create the two attributes userId and profileId)
  * Sequelize will automatically create this model C (if not exists) and define appropriate foreign keys on it
  * getBars()
  * countBars()
  * hasBar()
  * hasBars()
  * setBars()
  * addBar()
  * addBars()
  * removeBar()
  * removeBars()
  * createBar()

```js
// 1. has One Many
User.hasOne(models.UserProfile, { foreignKey: { name: "userID", allowNull: false } });
db.food.hasMany(db.meal, {as : 'Food', foreignKey : 'foodID'});

// 2. belongs to
Match.belongsTo(models.User, {foreignKey: { name: "userID" } });

import { DataTypes, Model, Sequelize } from "sequelize";

export default (sequelize: Sequelize) => {
  class Match extends Model {
    static associate(models): void {
      Match.belongsTo(models.User, {
        foreignKey: { name: "userID" }
      });
      Match.belongsTo(models.Room, {
        foreignKey: { name: "roomID", allowNull: false }
      });
    }
  }
  return Match.init({
      id: {
        type: DataTypes.UUID,
        defaultValue: DataTypes.UUIDV4,
        primaryKey: true,
      },
    },
    { sequelize, modelName: "Match", ...modelOptions["general"] },
  );
};

// 3. automatically creates
// This creates a junction table `foo_bar` with fields `fooId` and `barId`
Foo.belongsToMany(Bar, { through: 'foo_bar' });
// This creates a junction table `foo_bar` with fields `fooId` and `barTitle`
Foo.belongsToMany(Bar, { through: 'foo_bar', targetKey: 'title' });
// This creates a junction table `foo_bar` with fields `fooName` and `barId`
Foo.belongsToMany(Bar, { through: 'foo_bar', sourceKey: 'name' });
// This creates a junction table `foo_bar` with fields `fooName` and `barTitle`
Foo.belongsToMany(Bar, { through: 'foo_bar', sourceKey: 'name', targetKey: 'title' });

const User = sequelize.define('user', { username: DataTypes.STRING, points: DataTypes.INTEGER }, { timestamps: false } );
const Profile = sequelize.define('profile', { name: DataTypes.STRING }, { timestamps: false } );
User.belongsToMany(Profile, { through: 'User_Profiles', foreignKey: "UserID"});
Profile.belongsToMany(User, { through: 'User_Profiles', foreignKey: "ProfileID"});
```

{% endtab %}
{% endtabs %}

## Relational algebra

```txt
# Find directors of current movies
{t: title | $$ \exists $$ s $$ \in $$ schedule [s(title) = t(title)]}

# Find the titles and the directors of all currently playing movies
{t: title, director | ∃s ∈schedule ∃m ∈ movie [s(title) = m(title) ∧ t(title) = m(title) ∧ t(director) = m(director)]}

# Find actors playing in every movie by Berto
{ a : actor |  y  movie [a(actor) = y(actor) m movie [m(dir) = ”Berto” t movie(m(title) = t(title)  t(actor) = y(actor))]]}
```

## ORM

{% tabs %}
{% tab title='python' %}

> sqlalchemy

* detached: Object, states which an object can have within a session
* dialect: Object, allows DB operations on a particular DB backend
* DBAPI: Python Database API Specification
* metadata: generally refers to "data that describes data"
* create_engine('DB', echo=True): echo for logging

* sqlalchemy.engine: not thread-safe
  * underlying DBAPI connection may not support shared access between threads
  * begin(): Transaction Instance

* sqlalchemy.engine.Engine: Connects a Pool and Dialect together
  * begin(): Return a context manager delivering a Connection
  * connect(): Return a new Connection object

* sqlalchemy.engine.Connection: not thread-safe
  * execute(): Executes SQL statement construct, returns ResultProxy

* sqlalchemy.engine.Transaction
  * not thread safe
  * close()
  * commit()
  * rollback()

* sqlalchemy.schema
* sqlalchemy.schema.column
  * Column(name, type, primary_key=F): Column in a database table

* sqlalchemy.schema.Table
  * Table()
  * drop(engine)
  * columns

* sqlalchemy.schema.MetaData
  * MetaData(): Thread-safe container object for read
  * create_all(): check existence of each individual table. CREATE if not

```py
# to_sql
engine = sqlalchemy.create_engine("postgresql://user:password@host:port/database")
```

{% endtab %}
{% endtabs %}

### Eager loading

{% tabs %}
{% tab title='django' %}

```py
# 1. Call user and parent
user = User.objects.all()
parent = user.prefetch_related('parent')
```

{% endtab %}
{% tab title='sequelize' %}

```js
// 1. Eager.js
User.belongsToMany(Profile, { through: 'User_Profiles' });
Profile.belongsToMany(User, { through: 'User_Profiles' });

/* Lazy */
const amidala = await User.create({ username: 'p4dm3', points: 1000 });
const queen = await Profile.create({ name: 'Queen' });
await amidala.addProfile(queen, { through: { selfGranted: false } });
const result = await User.findOne({ where: { username: 'p4dm3' }, include: Profile });
console.log(result);

/* Eager */
const amidala = await User.create({
  username: 'p4dm3', points: 1000,
  profiles: [{ name: 'Queen', User_Profile: { selfGranted: true } }]
}, { include: Profile });

const result = await User.findOne({ where: { username: 'p4dm3' }, include: Profile });
```

{% endtab %}
{% endtabs %}

### N + 1 selects

{% tabs %}
{% tab title='django' %}

```py
# 1. Select video with comments
comments = Comment.objects.filter(video__title__starts_with='The').select_related('video').all()
```

{% endtab %}
{% tab title='sql' %}

```sql
-- 1. Get all wheels in each cars
SELECT * FROM Cars;
-- BAD: For each Cars, N additional selects
SELECT * FROM Wheel WHERE CarId = ?
-- GOOD
SELECT * FROM Wheel
```

{% endtab %}
{% endtabs %}
