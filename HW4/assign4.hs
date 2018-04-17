import System.Environment
import Data.List
import Data.Char
import Data.Set

assign4 :: String -> String -> IO [String]
assign4 filePath word = do
    fileContentsLS <- readFile (filePath)

    let loweredContents = lowerString (fileContentsLS)
    let wordsFromFile = lines loweredContents

    let wordToLowerCase = lowerString (word)
    let wordPermutations = generatePermutations wordToLowerCase

    let resultsWithDuplicates = checkPermutations wordPermutations wordsFromFile
    let setResults = Data.Set.fromList(resultsWithDuplicates)
    let results = toList setResults
    return results


lowerString str = [toLower loweredString | loweredString <- str]



generatePermutations baseString = do
    let perms = permutations (baseString)
    return perms !! 0

checkPermutations xs (y) = [x | x <- xs, x `elem` y]
