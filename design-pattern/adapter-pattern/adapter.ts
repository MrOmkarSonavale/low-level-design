abstract class IReport {
    abstract generateReport(): string;
};

class XmlDataProivider {
    getData(): string {
        return "<data>Data from XML</data>";
    }
};

class XmlDataProividerAdapter extends IReport {
    private xmlDataProvider: XmlDataProivider;

    constructor(xmlDataProvider: XmlDataProivider) {
        super();
        this.xmlDataProvider = xmlDataProvider;
    }



    generateReport(): string {

        const xmlData = this.xmlDataProvider.getData();
        const jsonData = this.convertXmlToJson(xmlData);
        return jsonData;
    }

    private convertXmlToJson(xmlData: string): string {
        return "{\"data\": \"Converted JSON from XML\"}";
    }
};

const x1 = new XmlDataProivider();
const adapter = new XmlDataProividerAdapter(x1);
console.log(adapter.generateReport());