# Proof of Concept - To identify/detect anomalies in game transactions using Machine Learning & Sagemaker
### C++ bot to generate RPG game sample data to train the algorithm
### Jupyter Notebook, working dataset, Sagemaker endpoint for quick tests included in this working sample
### 2018-GAM310 - Presented at re:Invent 2018, talk GAM-310

A working demo for a proof-of-concept to use a basic binary classification algorithm to detect and flag anomalous/fraudulent gameplay transactions in a game report.

The bot (generateData.cpp and generateData.h) can be compiled and run to generate randomized gameplay data for a over-simplified Role Playing Game (RPG). The command to compile the code is inside the header file.

The generated data is used to train the algorithm which is then hosted as a Sagemaker endpoint to make predictions of the game data.

Run the cli.sh shell script to run basic tests, or customise it and run your own tests against the pretrained & hosted model.

Refer to the Jupyter notebook in the repo as well as the presentation that provides the background.

A couple colleagues also developed a video tutorial that elaborates the proof of concept available here: https://www.aws.training/Details/Video?id=41827
