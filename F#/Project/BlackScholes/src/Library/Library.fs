module Library
open FSharp.Configuration
open System
open MathNet.Numerics.Distributions


type Derivative = {
    name: string;
    strikePrice: float; 
    currentPrice: float; 
    riskFreeInterestRate: float; 
    timeToMaturity: float; 
    sigma: float
}

type BlackScholesConfig = {
    portfolio: List<Derivative>
}


type BlackScholes(strikePrice: float, currentPrice: float, riskFreeInterestRate: float, timeToMaturity: float, sigma: float) = 
    let r = riskFreeInterestRate
    let T = timeToMaturity
    let K = strikePrice
    let S = currentPrice
    let normal = new Normal(0, 1);

    member this.D1: float = 
        let num = Math.Log(S / K) + (r + (sigma ** 2.0) / 2.0) * T
        let den = sigma * Math.Sqrt(T)
        num / den

    member this.DeltaCall: float = normal.CumulativeDistribution(this.D1)
    member this.DeltaPut: float = -normal.CumulativeDistribution(-this.D1)

    member this.GetCallPrice = 
        S * normal.CumulativeDistribution(this.D1) - K * Math.Exp(-r * T) * normal.CumulativeDistribution(this.D1 - sigma * Math.Sqrt(T))
    
    member this.GetPutPrice = 
        K * Math.Exp(-r * T) * normal.CumulativeDistribution(sigma * Math.Sqrt(T) - this.D1) - S * normal.CumulativeDistribution(-this.D1)
    
    member this.GetPutPriceSimpler = 
        this.GetCallPrice + K / Math.Exp(r * T) - S


let handlePortfolio(portfolio: List<Derivative>) = 
    for derivative in portfolio do
        printfn "Current derivative: %s" derivative.name

        let model = new BlackScholes(
            strikePrice=derivative.strikePrice,
            currentPrice=derivative.currentPrice,
            riskFreeInterestRate=derivative.riskFreeInterestRate,
            timeToMaturity=derivative.timeToMaturity / 365.0,
            sigma=derivative.sigma
        )

        printfn "D1: %f" model.D1
        printfn "Delta call: %f" model.DeltaCall
        printfn "Delta put: %f"  model.DeltaPut
        printfn "Call price: %f" model.GetCallPrice
        printfn "Put price: %f" model.GetPutPrice
        let callIntrinsicValue: float = Math.Max(0, derivative.currentPrice - derivative.strikePrice)
        printfn "Call intrinsic value: %f" callIntrinsicValue
        let callSpeculativePremium: float = model.GetCallPrice - callIntrinsicValue
        printfn "Call speculative premium: %f" callSpeculativePremium
        let putIntrinsicValue: float = Math.Max(0, derivative.strikePrice - derivative.currentPrice)
        printfn "Put intrinsic value: %f" putIntrinsicValue
        let putSpeculativePremium: float = model.GetPutPrice - putIntrinsicValue
        printfn "Put speculative premium: %f" putSpeculativePremium

        printfn "\n===================================\n"