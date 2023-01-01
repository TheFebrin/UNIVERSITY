open System
open Library
open System.IO
open System.Text.Json
open FSharp.Configuration
open MathNet.Numerics.Distributions



[<EntryPoint>]
let main args =

    let readFile (filePath:string) =
        use streamReader = new StreamReader(filePath)
        streamReader.ReadToEnd()

    let config =
        let configText = readFile "config.json"
        JsonSerializer.Deserialize<BlackScholesConfig>(configText)


    handlePortfolio config.portfolio


    0 // return an integer exit code