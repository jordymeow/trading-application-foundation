# Trading Application Foundation
This is a base / foundation for a trading application (automation or anything else). The aim is to have a stable and solid system using C++ with Boost on the server side, and C# with WPF on the client side.

# The Project
The end result in sight is a server-client which would provide the basis for an optimized trading platform. It would include all the basic functions needed for implementing your own customized trading tool. This platform will be neutral to any market data providers and brokers ; connectivity to market data providers and brokers will be seamlessly accessible through abstracted interfaces and classes.

The server would host the critical functions (market data reception from data sources, strategy execution and order generation to brokers) ie.: where execution speed is paramount, while the client would act as a control and analysis platform (monitoring, backtesting of strategies, live strategy implementation to server).

This project was started by Jordy Meow and Sieu Luong.

## Overall progress
- What is being implemented now:
- Infrastructure & Framework
- The Yahoo Market Data paradigm
- A basic client (only for testing purposes)

## What will be implemented:
- The .NET API for the client side
- Interactive Brokers (Broker) paradigm
- Bloomberg (Market Data) paradigm
- Reuters (Market Data) paradigm
