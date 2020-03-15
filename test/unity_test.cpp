#include <unity.h>
#include <Arduino.h>
#include <UILayout.h>
#include <Widget.h>
#include <SSD1306Geometry.h>
#include <UI.h>
#include <ThermostatManager.h>
#include <HttpController.h>

SSD1306Wire display(I2C_DISPLAY_ADDRESS, D3, D4);
DHTesp dht;

Rectangle* makeRectangle1() {
    Point p1,p2;
    p1.x = 0;
    p1.y = 0;
    p2.x = 12;
    p2.y = 10;
    Rectangle* p1p2 = new Rectangle(p1, p2);
    return p1p2;
}

Rectangle* makeRectangle2() {
    Point q1,q2;
    q1.x = 10;
    q1.y = 0;
    q2.x = 20;
    q2.x = 20;
    Rectangle* q1q2 = new Rectangle(q1, q2);
    return q1q2;
}

void test_intersects_true(){
    Rectangle* r1 = makeRectangle1();
    Rectangle* r2 = makeRectangle2();
    TEST_ASSERT_TRUE(r1->intersects(r2));
}

void test_getters() {
    Rectangle* r1 = makeRectangle1();
    TEST_ASSERT_EQUAL_UINT8(12, r1->getWidth());
    TEST_ASSERT_EQUAL_UINT8(10, r1->getHeight());
}

void testTemperatureWidget_getTemperatureString() {
    TemperatureWidget fixture;
    
    String tempStr = fixture.getTemperatureString();
    TEST_ASSERT_NOT_NULL(tempStr);
    Serial.println(tempStr);
    TEST_ASSERT_EQUAL_STRING("T 0.0", tempStr.c_str());
    fixture.setTemperature(32.4);
    tempStr = fixture.getTemperatureString();
    TEST_ASSERT_NOT_NULL(tempStr);
    Serial.println(tempStr);
    TEST_ASSERT_EQUAL_STRING("T 32.4", tempStr.c_str());
}

void testTemperatureWidget_getHumidityString() {
    TemperatureWidget fixture;
    
    String humStr = fixture.getHumidityString();
    TEST_ASSERT_NOT_NULL(humStr);
    Serial.println(humStr);
    TEST_ASSERT_EQUAL_STRING("H 0.0", humStr.c_str());
    fixture.setHumidity(23.4);
    humStr = fixture.getHumidityString();
    TEST_ASSERT_NOT_NULL(humStr);
    Serial.println(humStr);
    TEST_ASSERT_EQUAL_STRING("H 23.4", humStr.c_str());
}

void testUILayout_canAdd_true(){
    Serial.println("testUILayout_canAdd");
    UILayout fixture;
    TemperatureWidget fakeWidget;
    TEST_ASSERT_TRUE(fixture.canAdd(&fakeWidget));
    TEST_ASSERT_NULL(fixture.getWidgets());
}

void testUILayout_addWidget() {
    UILayout fixture;
    TemperatureWidget fake1;
    TemperatureWidget fake2;
    
    Widget* pFake1 = &fake1;
    fixture.addWidget(pFake1);
    fixture.addWidget(&fake2);
    WidgetNode* widgets = fixture.getWidgets();
    Serial.println("Checking widgets list");
    TEST_ASSERT_NOT_NULL(widgets);
    TEST_ASSERT_TRUE( &(fake2) == widgets->widget);

    Serial.println("Accessing widget node");
    Rectangle* r1 = makeRectangle2();
    fake1.setBoundary(r1);
    Serial.println("Checking widget positions in list");
    TEST_ASSERT_NOT_NULL(widgets->next);
    TEST_ASSERT_NOT_NULL(widgets->next->widget);
    TEST_ASSERT_TRUE( &(fake1) == widgets->next->widget);
}

void testUILayout_render() {
    Serial.println("Init testUILayout_render");
    UILayout* fixture = new UILayout; 
    TemperatureWidget* tmp = new TemperatureWidget;
    Rectangle* pos = makeRectangle1();
    Serial.println("Init complete");
    tmp->setBoundary(pos);
    fixture->addWidget(tmp);
    Serial.println("Clearing");
    display.clear();
    Serial.println("Rendering");
    fixture->render(display);
    Serial.println("Displaying");
    display.display();
    TEST_PASS();
}

void testUI_render(){
    UI* fixture = new UI(&display);
    UILayout* lout = new UILayout; 
    TemperatureWidget* tmp = new TemperatureWidget;
    Rectangle* pos = new Rectangle(Point{0,0}, Point{34,32});
    Serial.println("Init test");
    tmp->setBoundary(pos);
    lout->addWidget(tmp);
    fixture->setUILayout(lout);
    Serial.println("Init complete");
    fixture->init();
    Serial.println("UI init done");
    fixture->render();
    TEST_PASS();
}

void testTemperatureManager_getThermostatReadings(){
    //reads two times in a row, the values should not be NAN
    thermostat::ThermostatManager* fixture = new thermostat::ThermostatManager(&dht);
    thermostat::ThermostatReadings res = fixture->getThermostatReadings();
    TEST_ASSERT_FLOAT_IS_NOT_NAN(res.humidity);
    TEST_ASSERT_FLOAT_IS_NOT_NAN(res.temperature);
    TEST_ASSERT_FLOAT_IS_NOT_NAN(res.heatIndex);
    res = fixture->getThermostatReadings();
    TEST_ASSERT_FLOAT_IS_NOT_NAN(res.humidity);
    TEST_ASSERT_FLOAT_IS_NOT_NAN(res.temperature);
    TEST_ASSERT_FLOAT_IS_NOT_NAN(res.heatIndex);
    delete fixture;
}

void testHttpController_registerHandlers() {
    thermostat::ThermostatManager* mgr = new thermostat::ThermostatManager(&dht);
    http::HttpController* fixture = new http::HttpController(mgr);
    fixture->registerHandlers();
    TEST_PASS();
    delete fixture;
    delete mgr;
}

void testSuite_UI(){
    RUN_TEST(testUI_render);
}

void testSuite_UILayout() {
    RUN_TEST(testUILayout_canAdd_true);
    RUN_TEST(testUILayout_addWidget);
    RUN_TEST(testUILayout_render);
}

void testSuite_SSDGeometry() {
    RUN_TEST(test_intersects_true);
    RUN_TEST(test_getters);
}

void testSuite_TemperatureWidget(){
    RUN_TEST(testTemperatureWidget_getTemperatureString);
    RUN_TEST(testTemperatureWidget_getHumidityString);
}

void testSuite_TemperatureManager() {
    RUN_TEST(testTemperatureManager_getThermostatReadings);
}

void testSuite_HttpController() {
    RUN_TEST(testHttpController_registerHandlers);
}

void setup(){
    Serial.begin(115200);
    display.init();
    display.setColor(WHITE);

    dht.setup(D6, DHTesp::DHT11);
    UNITY_BEGIN();
    Serial.println("####testSuite_SSDGeometry");
    testSuite_SSDGeometry();
    Serial.println("####testSuite_TemperatureWidget");
    testSuite_TemperatureWidget();
    Serial.println("####testSuite_UILayout");
    testSuite_UILayout();
    Serial.println("####testSuite_UI");
    testSuite_UI();
    Serial.println("####testSuite_TemperatureManager");
    testSuite_TemperatureManager();
    Serial.println("####testSuite_HttpController");
    testSuite_HttpController();
    UNITY_END();
}

void loop() {
     UNITY_BEGIN();
     UNITY_END();
}